let (|?>) = (fn, opt) =>
  switch (opt) {
  | None => None
  | Some(value) => fn(value)
  };

let (|?>>) = (fn, opt) =>
  switch (opt) {
  | None => None
  | Some(value) => Some(fn(value))
  };

let (|?) = (opt, default) =>
  switch (opt) {
  | None => default
  | Some(value) => value
  };

let parseRepositoryResponse = rawResponse =>
  switch (rawResponse##viewer##repositories##nodes) {
  | None => None
  | Some(nodes) => nodes
  };
/*ReasonReact.array(
    Array.map(
      node =>
        switch (node) {
        | None => <div> (ReasonReact.string("None")) </div>
        | Some(node) =>
          let star =
            node##viewerHasStarred ?
              {js|★|js} : {js|☆|js};
          <div>
            (
              ReasonReact.string(
                string_of_int(node##stargazers##totalCount)
                ++ " "
                ++ star
                ++ ": "
                ++ node##name,
              )
            )
          </div>;
        },
      response |> parseRepositoryResponse,
    ),
  )*/