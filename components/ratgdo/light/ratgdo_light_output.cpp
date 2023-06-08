#include "ratgdo_light_output.h"
#include "../ratgdo_state.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ratgdo {

    using namespace esphome::light;

    static const char* const TAG = "ratgdo.light";

    void RATGDOLightOutput::dump_config()
    {
        ESP_LOGCONFIG("", "RATGDO Light");
    }
    void RATGDOLightOutput::on_light_state(esphome::ratgdo::LightState state)
    {
        ESP_LOGD(TAG, "on_light_state: %d", state);
        if (this->light_state_) {
            this->light_state_->current_values.set_state(state == LightState::LIGHT_STATE_ON);
            this->light_state_->remote_values.set_state(state == LightState::LIGHT_STATE_ON);
            this->light_state_->publish_state();
        }
    }
    LightTraits RATGDOLightOutput::get_traits()
    {
        auto traits = LightTraits();
        traits.set_supported_color_modes({ light::ColorMode::ON_OFF });
        return traits;
    }

    void RATGDOLightOutput::write_state(light::LightState* state)
    {
        bool binary;
        state->current_values_as_binary(&binary);
        if (binary) {
            ESP_LOGD(TAG, "output call lightOn");
            this->parent_->lightOn();
        } else {
            ESP_LOGD(TAG, "output call lightOff");
            this->parent_->lightOff();
        }
    }

} // namespace ratgdo
} // namespace esphome
