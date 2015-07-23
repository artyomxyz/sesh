# sesh
Shell

## Compilation 
using `make` in *sesh/src* catalogue.

## Launching program
`..bin/sesh`

## Setting up Git
Tell *Git* your *name* and  the *email address* that will be associated with your Git commits
```
git config --global user.name "YOUR NAME"
git config --global user.email "YOUR EMAIL ADDRESS"
```

##Authenticating with GitHub from Git
You should generate a new **SSH key**.
1. `ssh-keygen -t rsa`
2. Click *Enter* three times, when terminal asked you a password.
3. `cat ~/.ssh/id_rsa.pub`
4. Copy SSH key 
```ssh-rsa 
	......... your@email.com
```
5. Paste it on the [github](https://github.com/settings/ssh) by adding new SSH key.


## Contribution
1. Clone repository
`git clone git@github.com:artemsmirnov/sesh.git`

2. Creating branch
`git checkout -b branch_name`

3. Indexing changes
`git add changed_file`

4. Committing changes
`git commit -m "commit message"`

5. Pushing changes
`git push origin branch_name`

6. Create pull request on [github](https://www.github.com) and inform a team leader.



