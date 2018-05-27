type orderDirection = [ | `ASC | `DESC];

module GetRepos = [%graphql
  {|
    query getRepos ($first: Int!, $direction: OrderDirection!){
      viewer {
        repositories(first: $first, orderBy: {field: STARGAZERS, direction: $direction}) {
          totalCount
          nodes {
            id
            name
            stargazers {
              totalCount
            }
            viewerHasStarred
          }
        }
      }
    }
|}
];

module GetReposQuery = ReasonApollo.CreateQuery(GetRepos);

let listItem = node => {
  let star = node##viewerHasStarred ? {js|★|js} : {js|☆|js};
  <li key=node##id className="list-group-item list-group-item-action">
    (
      ReasonReact.string(
        star
        ++ " Star ("
        ++ string_of_int(node##stargazers##totalCount)
        ++ ")"
        ++ " : "
        ++ node##name,
      )
    )
  </li>;
};

let component = ReasonReact.statelessComponent("RepositoryList");

let make = (~first, ~direction, _children) => {
  ...component,
  render: _self => {
    let reposQuery = GetRepos.make(~first, ~direction, ());
    <GetReposQuery variables=reposQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | Loading => <div> (ReasonReact.string("Loading ...")) </div>
             | Error(_error) => ReasonReact.null
             | Data(response) =>
               <ul className="list-group">
                 (
                   switch (response##viewer##repositories##nodes) {
                   | None => <li> (ReasonReact.string("No Repos")) </li>
                   | Some(nodes) =>
                     ReasonReact.array(
                       Array.map(
                         node =>
                           switch (node) {
                           | None =>
                             <li className="list-group-item">
                               (ReasonReact.string("None"))
                             </li>
                           | Some(node) => node |> listItem
                           },
                         nodes,
                       ),
                     )
                   }
                 )
               </ul>
             }
         )
    </GetReposQuery>;
  },
};