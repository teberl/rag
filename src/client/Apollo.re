let logout = () => ();

/* Create an HTTP Link */
let httpLink =
  ApolloLinks.createHttpLink(~uri="https://api.github.com/graphql", ());

/* Create a Link that puts an Authorization header in context */
let contextHandler = () => {
  let token = Token.github;
  let headers = {
    "headers": {
      "authorization": {j|Bearer $token|j},
    },
  };
  headers;
};

let authLink = ApolloLinks.createContextLink(contextHandler);

/* Create a Link that handles 401 error responses */
let errorHandler = errorResponse =>
  switch (errorResponse##networkError) {
  | Some(error) => Js.Console.error(error)
  /*
   since i encountered an runtime error with this code i will only log for now
   match[0].statusCode //  cannot call statusCode of undefined

     if (error##statusCode == 401) {
       logout();
     } else {
       ();
     }
   */
  | None => ()
  };

let errorLink = ApolloLinks.createErrorLink(errorHandler);

/* Default in memory cache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

/* Create the ApolloClient */
let instance =
  ReasonApollo.createApolloClient(
    ~cache=inMemoryCache,
    ~link=ApolloLinks.from([|authLink, errorLink, httpLink|]),
    (),
  );