#pragma once

#include <monkey/bullet/rigidbody.h>
#include "btBulletDynamicsCommon.h"

class InputMethod;

class Vehicle : public BulletRigidBody {
public:
    Vehicle(const ITab&);
    void Start() override;

    void Update(double) override;
    btRaycastVehicle* getVehicle();


private:
    InputMethod * m_input;
    btRaycastVehicle* m_vehicle;
    float m_chassisMass;

    float m_engineForce;
    float m_defaultBreakingForce;
    float m_breakingForce;

    float m_maxEngineForce;
    float m_maxBreakingForce;

    float m_vehicleSteering;
    float m_steeringIncrement;
    float m_steeringClamp;
    float m_wheelRadius;
    float m_wheelWidth;
    float m_wheelFriction;
    float m_suspensionStiffness;
    float m_suspensionDamping;
    float m_suspensionCompression;
    float m_rollInfluence;
    btScalar m_suspensionRestLength;
    btRaycastVehicle::btVehicleTuning m_tuning;
};


inline btRaycastVehicle * Vehicle::getVehicle() {
    return m_vehicle;
}