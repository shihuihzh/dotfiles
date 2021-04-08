# ~/.profile: executed by the command interpreter for login shells.
# This file is not read by bash(1), if ~/.bash_profile or ~/.bash_login
# exists.
# see /usr/share/doc/bash/examples/startup-files for examples.
# the files are located in the bash-doc package.

# the default umask is set in /etc/profile; for setting the umask
# for ssh logins, install and configure the libpam-umask package.
#umask 022

# if running bash
if [ -n "$BASH_VERSION" ]; then
    # include .bashrc if it exists
    if [ -f "$HOME/.bashrc" ]; then
	. "$HOME/.bashrc"
    fi

    # include .bash_profile if it exists
    if [ -f "$HOME/.bash_profile" ]; then
	. "$HOME/.bash_profile"
    fi
fi

# set PATH so it includes user's private bin if it exists
if [ -d "$HOME/bin" ] ; then
    PATH="$HOME/bin:$PATH"
fi

export _JAVA_AWT_WM_NONREPARENTING=1
export GOPATH=$HOME/DEV/go
export M2_HOME=$HOME/DEV/Soft/apache-maven-3.5.3
export JAVA_HOME=$HOME/DEV/Soft/Java/jdk-11.0.2
export JDK_HOME=$JAVA_HOME
export PATH=$JAVA_HOME/bin:$PATH:$HOME/.scripts:$M2_HOME/bin

#export MOZ_GTK_TITLEBAR_DECORATION=system
export GTK_IM_MODULE=ibus
export XMODIFIERS=@im=ibus
export QT_IM_MODULE=ibus
# export GTK_IM_MODULE=fcitx
# export QT_IM_MODULE=fcitx
# export XMODIFIERS="@im=fcitx"
export TERMINAL=alacritty
export PATH="$HOME/.cargo/bin:$PATH"

ibus-daemon -drx
# fcitx-autostart &
/usr/bin/kdeconnect-indicator &
/usr/lib/kdeconnectd &
/usr/bin/blueman-tray &

# NVM for nodejs
export NVM_DIR="$([ -z "${XDG_CONFIG_HOME-}" ] && printf %s "${HOME}/.nvm" || printf %s "${XDG_CONFIG_HOME}/nvm")"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh" # This loads nvm
