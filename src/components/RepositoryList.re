module GetRepos = [%graphql
  {|
    query getRepos ($first: Int!, $direction: OrderDirection!){
      viewer {
        repositories(first: $first, orderBy: {field: STARGAZERS, direction: $direction}) {
          nodes {
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

let component = ReasonReact.statelessComponent("RepositoryList");

let make = _children => {
  ...component,
  render: _self => {
    let reposQuery = GetRepos.make(~first=20, ~direction=`DESC, ());
    <GetReposQuery variables=reposQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | NoData => <div> (ReasonReact.string("No Data")) </div>
             | Loading => <div> (ReasonReact.string("Loading ...")) </div>
             | Error(_error) => <div> (ReasonReact.string("Error")) </div>
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
                           | Some(node) =>
                             let star =
                               node##viewerHasStarred ?
                                 {js|★|js} : {js|☆|js};
                             <li
                               className="list-group-item list-group-item-action">
                               (
                                 ReasonReact.string(
                                   string_of_int(node##stargazers##totalCount)
                                   ++ " "
                                   ++ star
                                   ++ ": "
                                   ++ node##name,
                                 )
                               )
                             </li>;
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