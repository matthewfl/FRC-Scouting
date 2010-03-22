// note this is included in the request file


Page(Debug, {
    write("Debug page\n");
    write(connection["q"]);
  });

Page(Home, {
    write(load("home"));
  });

Page(js, {
    write(load("jquery"));
    write("\n\n\n");
    write(load("myJs"));
  });

Page(style, {
    write(load("css"));
  });
