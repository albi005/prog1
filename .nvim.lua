local dap = require('dap')

dap.configurations.c = {
    {
        name = "Run C program",
        type = "cppdbg",
        request = "launch",
        program = function()
            vim.cmd('!gcc ' .. vim.fn.expand('%') .. ' -g')
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
