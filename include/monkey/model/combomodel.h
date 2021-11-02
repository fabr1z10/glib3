//#include <monkey/assets/model.h>
//#include <monkey/imesh.h>
//
//// a model with only one mesh
//class ComboModel : public Model {
//public:
//    ComboModel ();
//    Bounds getBounds() const override;
//    void draw (Shader*, int offset = 0, int count = 0) override;
//    std::vector<std::string> getAnimations() const override;
//    std::string getDefaultAnimation() const override ;
//    ShaderType GetShaderType() const override;
//    void addModel (std::shared_ptr<Model>);
//private:
//    std::vector<std::shared_ptr<Model>> m_models;
//    //std::vector<std::shared_ptr<IMesh>> m_meshes;
//
//};