//------------------------------------------------------------------------------------------------//
// Register Coffee modules
//
// This modules list is order dependent, those are initialized and updated in this order, then
// finalized in the ascending order.
// The Coffee application register itself at the end.
//------------------------------------------------------------------------------------------------//

COFFEE_RegisterModule(resource::Manager);
COFFEE_RegisterModule(input::Module);
COFFEE_RegisterModule(audio::Module);
COFFEE_RegisterModule(graphics::Module);
COFFEE_RegisterModule(ui::WindowManager);
COFFEE_RegisterModule(plugins::Module);
COFFEE_RegisterModule(physics::World);
COFFEE_RegisterModule(scene::World);


