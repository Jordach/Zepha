zepha.register_block("zeus:default:sandstone", {
    name = "Sandstone",
    model = "base:block",
    textures = {"zeus:default:sandstone"},
    toughness = {
        hand = 14,
        pick = 3
    },
    drop = "zeus:default:sand",
    on_break_client = function(pos)
        zepha.add_entity("zeus:default:dropped_item", vector.add(pos, v(0.5)),
            {object = zepha.registered_blocks["zeus:default:sandstone"].drop});
    end
})