open Resync;
open Refetch;
%raw
{|require('isomorphic-fetch')|};
%raw
{|
  const debugHttp = require('debug-http');
  debugHttp();
|};
/* simple post */
post("http://httpbin.org/post", `String("datathings"))
|> Future.flatMap(
     fun
     | Response.Ok(_, response) => Response.text(response)
     | Response.Error({reason}, _) => Future.from(reason),
   )
|> Future.whenResolved(text => Js.log(text));