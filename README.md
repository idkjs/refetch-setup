# Using Refetch

Doesn't look like you have to install `bs-fetch` unless you are running the [`src/png`](./src/png.re) and [`src/github`](./src/png.re) examples. You can test it by taking `bs-fetch` out of `bsconfig.json` and seeing what breaks.

You do have to have a `fetch` binding like `node-fetch` or `isomorphich-fetch` for example.

To run [`src/png`](./src/png.re) add two packages:

```sh
pnpm i stream-to-buffer console-png
pnpm i stream-to-buffer console-png
# install next branch of `bs-fetch`
pnpm i reasonml-community/bs-fetch#next
```

# Build
```
npm run build
```

# Use in Production

See: [https://github.com/CodaProtocol/coda/blob/develop/frontend/website/src/bindings/ReFetch.re](https://github.com/CodaProtocol/coda/blob/develop/frontend/website/src/bindings/ReFetch.re)

I think this just reimplements `refetch` in a binding.

```reason
include Bs_fetch;

// Polyfill fetch during prerendering
[%raw "require('isomorphic-unfetch')"];
let fetch =
    (
      ~method_=?,
      ~headers=?,
      ~body=?,
      ~referrer=?,
      ~referrerPolicy=?,
      ~mode=?,
      ~credentials=?,
      ~cache=?,
      ~redirect=?,
      ~integrity=?,
      ~keepalive=?,
      resource,
    ) =>
  fetchWithInit(
    resource,
    RequestInit.make(
      ~method_?,
      ~headers=?Option.map(HeadersInit.make, headers),
      ~body?,
      ~referrer?,
      ~referrerPolicy?,
      ~mode?,
      ~credentials?,
      ~cache?,
      ~redirect?,
      ~integrity?,
      ~keepalive?,
      (),
    ),
  );
```


# Editor
If you use `vscode`, Press `Windows + Shift + B` it will build automatically
