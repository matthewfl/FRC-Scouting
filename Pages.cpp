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

Page(enterMatch, {
    vector<string> out;
    string input = connection["game"];
    boost::split(out, input, boost::is_any_of("\t "));
    // [time, "am/pm", match#, red1, red2, red3, blue1, blue2, blue3, redScore, blueScore]
    if(out.size() < 8)
      return write("false");
    stringstream q;
    q << "INSERT INTO match VALUES (";
    q << out[2] << ", " 
      << out[3] << ", " << out[4] << ", " << out[5] << ", "
      << out[6] << ", " << out[7] << ", " << out[8] << ");";
    parent->db->query(q.str());
    write("true");
  });

Page(matchInfo, {
    stringstream q;
    q << "SELECT red1, red2, red3, blue1, blue2, blue3 FROM match WHERE number="
      << connection["num"] << ";";
    vector<string> ret = parent->db->query(q.str())[0];
    for(vector<string>::iterator it=ret.begin(); it!=ret.end(); it++) {
      write(*it);
      write("\n");
    }
  });
