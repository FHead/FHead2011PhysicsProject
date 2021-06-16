
path=$1
url=$2

# split the "main repo"
git subtree split -P $1 -b NewBranch$1

# Create your repository, and get git url

# add remote for branch
git remote add submodule $2

# push the submodule
git push -u submodule NewBranch$1:master

# remove path
git rm -r $1

# Stage and commit changes
git add -A $1
git commit -m "Remove $1 for submodule replacement"

# add the submodule
git submodule add -b master $2 $1

# and once your submodule is added commit the .gitmodules file
git add .gitmodules
git commit -m "Added $1 as submodule"

git remote rm submodule
