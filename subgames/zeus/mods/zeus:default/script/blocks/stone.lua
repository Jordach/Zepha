zepha.register_block("zeus:default:stone", {
    name = "Stone",
    model = "base:block",
    textures = {"zeus:default:stone"},
    toughness = {
        hand = 14,
        pick = 3
    },
    drop = "zeus:default:cobblestone",
    on_break_client = function(pos)
        zepha.add_entity("zeus:default:dropped_item", vector.add(pos, v(0.5)),
            {object = zepha.registered_blocks["zeus:default:stone"].drop});
    end
})