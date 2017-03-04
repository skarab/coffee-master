#include "system/graphics/frame/picker/graphics_frame_picker.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
namespace graphics
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(FramePicker);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePicker::FramePicker()
    {
        COFFEE_CreateSingleton(FramePicker);

        _Material = resource::Manager::Get().Load(
            storage::Path("/coffee/import/shaders/others/picker.material"));
    }

    //----------------------------------------------------------------------------------------//

    FramePicker::~FramePicker()
    {
        COFFEE_DestroySingleton(FramePicker);
    }

}
}
