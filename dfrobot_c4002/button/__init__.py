import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_CONFIG

from .. import CONF_C4002_ID, C4002Component, dfrobot_c4002_ns

C4002RefreshButton = dfrobot_c4002_ns.class_(
    "C4002RefreshButton", button.Button, cg.Component
)

CONF_REFRESH_PARAMETERS = "refresh_parameters"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_C4002_ID): cv.use_id(C4002Component),
        cv.Optional(CONF_REFRESH_PARAMETERS): button.button_schema(
            C4002RefreshButton,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:refresh",
        ),
    }
)


async def to_code(config):
    if refresh_config := config.get(CONF_REFRESH_PARAMETERS):
        b = await button.new_button(refresh_config)
        await cg.register_parented(b, config[CONF_C4002_ID])
