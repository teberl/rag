# R.A.G

## ReasonML, Apollo and GitHub API v4

### Github personal access token

Currently you need your own _Personal access token_ in order to use this project.
Please see more information [here](https://github.com/settings/tokens).

To use all available features request the following scopes

```
user:email
public_repo
read:repo_hook
read:user
repo:status
repo_deployment
```

### Private token module

After you created your token you can create a `module Token` with a `gihtub` variable.
And if you put in in a private folder, it is already in the git ignore.

```

private
  |__ 
      Token.re

let github = "TOKEN"
```

### Schema Introspection

GraphQL is introspective. This means you can query a GraphQL schema for details about itself.

To get the gihtub graphql schema needed for this project please execute the following command from the commandline inside your project folder.

`yarn send-introspection-query https://api.github.com/graphql --headers "Authorization: bearer TOKEN"`

[TLDR; GraphQL Introspection](http://graphql.org/learn/introspection/)


### Running the project 

We need two separate terminals in order to run the project

1. `npm install`
2. `npm run bs` // first terminal for compiling _reason_ to _javascript_
3. `npm start`  // second terminal starts the webpack dev server
  
