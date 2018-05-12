# R.A.G

## ReasonML, Apollo and GitHub API v4

Currently you need your own _Personal access token_ in order to use this project.
Please see more information [here](https://github.com/settings/tokens).

To use all available features request the following scopes

```
user
public_repo
repo
repo_deployment
repo:status
read:repo_hook
read:org
read:public_key
read:gpg_key
```

After you created your token you can create a `module Token` with a `gihtub` variable.
And if you put in in a private folder, it is already in the git ignore.

```

private
  |__ 
      Token.re

let github = "TOKEN"
```

` yarn send-introspection-query https://api.github.com/graphql --headers "Authorization: bearer TOKEN"`
