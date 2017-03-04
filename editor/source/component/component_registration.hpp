//------------------------------------------------------------------------------------------------//
// Register all component types into the GUI
//------------------------------------------------------------------------------------------------//
Register<scene::Transform>();
Register<scene::Bounding>();
Register<graphics::ComponentMesh>();
Register<graphics::ComponentLightDirectional>();
Register<graphics::ComponentLightPoint>();
Register<graphics::ComponentLightIES>();
Register<graphics::ComponentLightSpot>();
Register<graphics::ComponentCameraPerspective>();
Register<graphics::ComponentSky>();
Register<physics::Box>();
Register<physics::Sphere>();
Register<physics::Cone>();
Register<physics::Capsule>();
Register<physics::Cylinder>();
Register<physics::ChamferCylinder>();
//Register<physics::Mesh>();
Register<physics::Character>();
Register<plugins::ComponentWrapper>();
Register<audio::ComponentSound>();
Register<coffee::component::FreeController>();
Register<coffee::component::CharacterController>();
