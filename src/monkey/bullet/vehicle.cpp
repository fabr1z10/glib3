#include <monkey/bullet/vehicle.h>
#include <monkey/engine.h>
#include <monkey/bullet/bulletworld.h>
#include <monkey/components/inputmethod.h>

#define CUBE_HALF_EXTENTS 1
Vehicle::Vehicle(const ITab& t) {
    m_engineForce = 0.f;
    m_vehicleSteering = 0.f;

    m_defaultBreakingForce = 10.f;
    m_breakingForce = 100.f;

    m_maxEngineForce = 100.f;  //this should be engine/velocity dependent
    m_maxBreakingForce = 100.f;

    m_steeringIncrement = t.get<float>("steering_increment", 0.04f);
    m_steeringClamp = t.get<float>("steering_clamp", 0.3f);
    m_wheelRadius = t.get<float>("wheel radius", 0.5f);
    m_wheelWidth = t.get<float>("wheel_width", 0.4f);
    m_wheelFriction = t.get<float>("wheel_friction", 1000);  //BT_LARGE_FLOAT;
    m_suspensionStiffness = t.get<float>("suspension_stiffness", 20.0f);
    m_suspensionDamping = t.get<float>("suspension_damping", 2.3f);
    m_suspensionCompression = t.get<float>("suspension_compression", 4.4f);
    m_rollInfluence = t.get<float>("roll_influence", 0.1f);
    m_suspensionRestLength = 0.6f;

    auto pos = t.get<glm::vec3>("pos");

    m_chassisMass = t.get<float>("chassis_mass");
    m_transform.setIdentity();
    m_transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
    auto world = Engine::get().GetRunner<BulletWorld>();
    auto dynamicsWorld = world->getDynamicsWorld();

    auto size = t.get<glm::vec3>("half_extents");

    // car chassis. now it's a box but you can make it more flexible later
    btCollisionShape* chassisShape = new btBoxShape(btVector3(size.x, size.y, size.z));
    m_body = world->addBody(m_chassisMass, m_transform, chassisShape);
    m_body->setActivationState(DISABLE_DEACTIVATION);



    // create vehicle
    btVehicleRaycaster* raycaster = new btDefaultVehicleRaycaster(world->getDynamicsWorld());
    m_vehicle = new btRaycastVehicle(m_tuning, m_body, raycaster);
    dynamicsWorld->addVehicle(m_vehicle);

    m_vehicle->setCoordinateSystem(0, 1, 2);

    float connectionHeight = -0.1f;

    btVector3 connectionPointCS0(CUBE_HALF_EXTENTS - (0.3 * m_wheelWidth), connectionHeight, 2 * CUBE_HALF_EXTENTS - m_wheelRadius);

    btVector3 wheelDirection(0.0f, -1.0f, 0.0f);
    btVector3 wheelAxle(-1.0f, 0.0f, 0.0f);

    // Be sure to attach the wheels not higher than the upper bounds of the hull of the vehicle chassis
    bool isFrontWheel = true;
    m_vehicle->addWheel(connectionPointCS0, wheelDirection, wheelAxle, m_suspensionRestLength, m_wheelRadius, m_tuning, isFrontWheel);
    connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS + (0.3 * m_wheelWidth), connectionHeight, 2 * CUBE_HALF_EXTENTS - m_wheelRadius);
    m_vehicle->addWheel(connectionPointCS0, wheelDirection, wheelAxle, m_suspensionRestLength, m_wheelRadius, m_tuning, isFrontWheel);
    connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS + (0.3 * m_wheelWidth), connectionHeight, -2 * CUBE_HALF_EXTENTS + m_wheelRadius);
    isFrontWheel = false;
    m_vehicle->addWheel(connectionPointCS0, wheelDirection, wheelAxle, m_suspensionRestLength, m_wheelRadius, m_tuning, isFrontWheel);
    connectionPointCS0 = btVector3(CUBE_HALF_EXTENTS - (0.3 * m_wheelWidth), connectionHeight, -2 * CUBE_HALF_EXTENTS + m_wheelRadius);
    m_vehicle->addWheel(connectionPointCS0, wheelDirection, wheelAxle, m_suspensionRestLength, m_wheelRadius, m_tuning, isFrontWheel);

    for (int i = 0; i < m_vehicle->getNumWheels(); i++)
    {
        btWheelInfo& wheel = m_vehicle->getWheelInfo(i);
        wheel.m_suspensionStiffness = m_suspensionStiffness;
        wheel.m_wheelsDampingRelaxation = m_suspensionDamping;
        wheel.m_wheelsDampingCompression = m_suspensionCompression;
        wheel.m_frictionSlip = m_wheelFriction;
        wheel.m_rollInfluence = m_rollInfluence;
    }


}

void Vehicle::Start() {
    m_input = m_entity->GetComponent<InputMethod>();
}

void Vehicle::Update(double dt) {

    if (m_input->isKeyDown(GLFW_KEY_LEFT)) {
        m_vehicleSteering += m_steeringIncrement;
        if (m_vehicleSteering > m_steeringClamp)
            m_vehicleSteering = m_steeringClamp;
    } else if (m_input->isKeyDown(GLFW_KEY_RIGHT)) {
        m_vehicleSteering -= m_steeringIncrement;
        if (m_vehicleSteering < -m_steeringClamp)
            m_vehicleSteering = -m_steeringClamp;
    } else {
        if (m_vehicleSteering > 0) {
            m_vehicleSteering -= m_steeringIncrement;
            m_vehicleSteering = std::max(0.0f, m_vehicleSteering);
        } else {
            m_vehicleSteering += m_steeringIncrement;
            m_vehicleSteering = std::min(0.0f, m_vehicleSteering);
        }
    }

    if (m_input->isKeyDown(GLFW_KEY_UP)) {
        if (m_input->isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
            m_engineForce = -m_maxEngineForce;
        } else {
            m_engineForce = m_maxEngineForce;
        }
        m_breakingForce = 0.f;
    } else if (m_input->isKeyDown(GLFW_KEY_DOWN)) {
        m_engineForce = 0.0f;
        m_breakingForce = m_defaultBreakingForce;
    }

    {
        int wheelIndex = 2;
        m_vehicle->applyEngineForce(m_engineForce, wheelIndex);
        m_vehicle->setBrake(m_breakingForce, wheelIndex);
        wheelIndex = 3;
        m_vehicle->applyEngineForce(m_engineForce, wheelIndex);
        m_vehicle->setBrake(m_breakingForce, wheelIndex);

        wheelIndex = 0;
        m_vehicle->setSteeringValue(m_vehicleSteering, wheelIndex);
        wheelIndex = 1;
        m_vehicle->setSteeringValue(m_vehicleSteering, wheelIndex);
    }

    //GLfloat matrix[16];
    auto trans = m_vehicle->getChassisWorldTransform();//.getOpenGLMatrix(&matrix[0]);
    auto mat = bulletToGlm(trans);
    m_entity->SetLocalTransform(mat);
    //BulletRigidBody::Update(dt);


}