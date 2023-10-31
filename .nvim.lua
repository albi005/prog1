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

-- use %.in if it exists
vim.keymap.set('n', '<Leader>r', function ()
    local input = vim.fn.expand('%:r') .. '.in'
    local exists = vim.fn.filereadable(input)
    if exists then
        vim.cmd('!gcc ' .. options .. ' "%" && ./a.out < "' .. input .. '"')
    else
        vim.cmd('!gcc ' .. options .. ' "%" && ./a.out')
    end
end)

-- compile and run in an interactive shell
-- <Leader>t
vim.keymap.set('n', '<Leader>t', ':!gcc ' .. options .. ' "%" && ./a.out |& tee /dev/tty<CR>', { noremap = true });

vim.keymap.set('n', '<Leader>s', ':!gcc ' .. options .. ' "%" `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer && ./a.out <CR>', { noremap = true });
