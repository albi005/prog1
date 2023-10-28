local dap = require('dap')

local options = "-lm -Wall -std=c99 -g -O0"

dap.configurations.c = {
    {
        name = "Run C program",
        type = "cppdbg",
        request = "launch",
        program = function()
            vim.cmd('!gcc ' .. options .. ' "' .. vim.fn.expand('%') .. '"')
            return 'a.out'
        end,
        cwd = '${workspaceFolder}',
        stopAtEntry = false,
        setupCommands = {
            {
                text = '-enable-pretty-printing',
                description =  'enable pretty printing',
                ignoreFailures = false
            },
        },
    },
}

dap.adapters.cppdbg = {
    id = 'cppdbg',
    type = 'executable',
    command = os.getenv'OPEN_DEBUG_PATH',
}

vim.keymap.set('n', '<Leader>r', ':!gcc ' .. options .. ' "%" && ./a.out < "%.in"<CR>', { noremap = true });
vim.keymap.set('n', '<Leader>t', ':!gcc ' .. options .. ' "%" && ./a.out <CR>', { noremap = true });
vim.keymap.set('n', '<Leader>s', ':!gcc ' .. options .. ' "%" `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer && ./a.out <CR>', { noremap = true });
