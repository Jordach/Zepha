local identifier = "zeus:world:plains"

local noise = {
   heightmap = {
       module = "add",
       sources = {{
           module = "const",
           value = -12
       }, {
           module = "add",
           sources = {{
               -- Elevation
               module = "scale_bias",
               source = {
                   module = "perlin",
                   frequency = 0.002,
                   octaves = 8
               },
               scale = 250,
               bias = -32
           }, {
               -- Features
               module = "scale_bias",
               source = {
                   module = "perlin",
                   frequency = 0.2,
                   octaves = 3,
               },
               scale = 6,
               bias = 6
           }}
       }}
   }
}

zepha.register_biome(identifier, {
   environment = {
       temperature = 15/100,
       humidity = 60/100,
       roughness = 20/100,
   },
   blocks = {
       top = "zeus:default:grass",
       soil = "zeus:default:dirt",
       rock = "zeus:default:stone"
   },
   groups = { natural = 1 },
   biome_tint = "#aaed45",
   noise = noise,
   structures = {
       tree
   }
})

return identifier