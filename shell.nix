{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    packages = with pkgs; [
        gcc
        gdb
        sourcekit-lsp
    ];
    shellHook = ''
        export PS1="\[\033[01;31m\]C!\[\033[00m\] ";
        export OPEN_DEBUG_PATH=${pkgs.vscode-extensions.ms-vscode.cpptools}/share/vscode/extensions/ms-vscode.cpptools/debugAdapters/bin/OpenDebugAD7;
    '';
}
