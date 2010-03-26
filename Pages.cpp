// note this is included in the request file

#define Write(n) write(string(n))

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
    for(int n=3; n<9; n++) {
      stringstream s;
      s << "SELECT * FROM team WHERE number=" << out[n];
      if(parent->db->query(s.str()).size()==0) {
	stringstream i;
	i << "INSERT INTO team VALUES (\"\", " << out[n] << ", 0, \"\" );";
	parent->db->query(i.str());
      }
    }
    write("true");
  });

Page(matchInfo, {
    stringstream q;
    q << "SELECT red1, red2, red3, blue1, blue2, blue3 FROM match WHERE number="
      << connection["num"] << ";";
    vector<vector<string> > ret = parent->db->query(q.str());
    if(ret.size() == 0)
      return;
    for(vector<string>::iterator it=ret[0].begin(); it!=ret[0].end(); it++) {
      write(*it);
      write("\n");
    }
  });



Page(matchTeamInfo, {
    stringstream q;
    q << "SELECT autoAtemp, autoMade, telAtemp, telMade, hangAtemp, hangMade, startLoc, pen, notes FROM teamMatch WHERE match=" << connection["match"] << " AND pos=" << connection["pos"] << ";";
    cout << q;
    vector<vector<string> > result = parent->db->query(q.str());
    if(result.size() == 0) {
      stringstream put;
      put << "INSERT INTO teamMatch VALUES (" 
	  << connection["team"] << ", "
	  << connection["pos"] << ", "
	  << connection["match"] << ", "
	  << "0, 0, 0, 0, 0, 0, \"\", \"\", 0);";
      parent->db->query(put.str());
      cout << put;
      write("0 0 0 0 0 0 0\n\n");
      return;
    }
    vector<string> data = result[0];
    write(data[0]);
    write(" ");
    write(data[1]);
    write(" ");
    write(data[2]);
    write(" ");
    write(data[3]);
    write(" ");
    write(data[4]);
    write(" ");
    write(data[5]);
    write(" ");
    write(data[6]);
    write("\n");
    write(boost::replace_all_copy(data[7], "\n", "\\n"));
    write("\n");
    write(boost::replace_all_copy(data[8], "\n", "\\n"));
  });

Page(matchTeamSave, {
    stringstream q;
    q << "UPDATE teamMatch SET"
      << " autoAtemp=" << connection["autoAtemp"]
      << ", autoMade=" << connection["autoMade"]
      << ", startLoc=" << connection["autoStart"]
      << ", telAtemp=" << connection["telAtemp"]
      << ", telMade=" << connection["telMade"]
      << ", hangAtemp=" << connection["hangAtemp"]
      << ", hangMade=" << connection["hangMade"]
      << ", notes=\"" << boost::replace_all_copy(connection["notes"], "\"", "\"\"")
      << "\", pen=\"" << boost::replace_all_copy(connection["pen"], "\"", "\"\"")
      << "\" WHERE team=" << connection["team"]
      << " AND match=" << connection["match"] << " ;";
    write(q.str());
    parent->db->query(q.str());

  });


Page(listTeamNum, {
    vector<vector<string> > r = parent->db->query("SELECT number FROM team ORDER BY number;");
    cout << r.size();
    for(vector<vector<string> >::iterator it=r.begin(); it!=r.end(); it++) {
      write((*it)[0]);
      write("\n");
    }
  });

Page(TeamInfo, {
    stringstream q;
    q << "SELECT * FROM teamMatch WHERE team=" << connection["num"];
    vector<vector<string> > res = parent->db->query(q.str());
    if(res.size()) {
      write("<table border='1'><tr><td>Auto Attempts</td><td>Auto Made</td><td>Tel Attempts</td><td>Tel Made</td><td>Hang Attempts</td><td>Hang Made</td></tr>");
      for(int a=0;a<res.size(); a++) {
	Write("<tr><td>");
	write(res[a][3]);
	Write("</td><td>");
	write(res[a][4]);
	Write("</td><td>");
	write(res[a][5]);
	Write("</td><td>");
	write(res[a][6]);
	Write("</td><td>");
	write(res[a][7]);
	Write("</td><td>");
	write(res[a][8]);
	Write("</td></tr>");
      }
    }
  });
