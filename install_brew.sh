
      #########.
     ########",#:
   #########',##".
  ##'##'## .##',##.
   ## ## ## # ##",#.
    ## ## ## ## ##'
     ## ## ## :##
      ## ## ##."

# Delete and reinstall Homebrew from Github repo
rm -rf $HOME/.brew
git clone --depth=1 https://github.com/Homebrew/brew /goinfre/$USER/brew

# Create .brewconfig script in home directory
cat > $HOME/.brewconfig.sh <<EOL
# HOMEBREW CONFIG

# Add brew to path
export PATH=/goinfre/$USER/brew/bin:\$PATH

# Set Homebrew temporary folders
export HOMEBREW_CACHE=/goinfre/$USER/Homebrew/Caches
export HOMEBREW_TEMP=/goinfre/$USER/Homebrew/Temp

mkdir -p \$HOMEBREW_CACHE
mkdir -p \$HOMEBREW_TEMP

# If NFS session
# Symlink Locks folder in /tmp
if df -T autofs,nfs \$HOME 1>/dev/null
then
  HOMEBREW_LOCKS_TARGET=/goinfre/$USER/Homebrew/Locks
  HOMEBREW_LOCKS_FOLDER=/goinfre/$USER/brew/var/homebrew

  mkdir -p \$HOMEBREW_LOCKS_TARGET
  mkdir -p \$HOMEBREW_LOCKS_FOLDER

  # Symlink to Locks target folders
  # If not already a symlink
  if ! [[ -L \$HOMEBREW_LOCKS_FOLDER && -d \$HOMEBREW_LOCKS_FOLDER ]]
  then
     echo "Creating symlink for Locks folder"
     rm -rf \$HOMEBREW_LOCKS_FOLDER
     ln -s \$HOMEBREW_LOCKS_TARGET \$HOMEBREW_LOCKS_FOLDER
  fi
fi
EOL

# Add .brewconfig sourcing in your .zshrc if not already present
if ! grep -q "# Load Homebrew config script" $HOME/.zshrc
then
cat >> $HOME/.zshrc <<EOL

# Load Homebrew config script
source \$HOME/.brewconfig.sh
EOL
cat >> $HOME/.bashrc <<EOL

# Load Homebrew config script
source \$HOME/.brewconfig.sh
EOL
fi

source $HOME/.brewconfig.sh
rehash
brew update

echo "\nPlease open a new shell to finish installation"
