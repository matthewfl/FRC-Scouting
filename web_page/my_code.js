///////////////////
// start my code //
///////////////////

var mode;

	


$(function () {
	$("#requireJS").remove();
	$(".content_action").hide();
	function mode_change () {
	    // the mode of the page changes
	    mode = $(this).val();
	    $(".content_action").hide();
	    switch(mode) {
	    case "chose":
		$("#welcomeAction").show();
		return; // what can I do
	    case "enterList": // enter the list of matches
		$("#enterList").show();
		return;
	    case "scoreMatch": // scoring the match
		$("#matchScouting").show();
		return;
	    }
	}
	
	mode_change.apply($("#mode")); // I think there is something in the jquery api that will do this
	$("#mode").change(mode_change);
	function match (number) {
	    $.ajax({
		    url: "/matchInfo?num="+number,
			success: function (list) {
			var teams = list.split("\n");
			$("#red1").html(teams[0]);
			$("#red2").html(teams[1]);
			$("#red3").html(teams[2]);
			$("#blue1").html(teams[3]);
			$("#blue2").html(teams[4]);
			$("#blue3").html(teams[5]);
		    }
		});
	    $("#matchAutoScoreAtmp").val(0);
	    $("#matchAutoScoreMade").val(0);
	    $("#matchTelScoreAtmp").val(0);
	    $("#matchTelScoreMade").val(0);
	    $("#matchTelHangAtmp").val(0);
	    $("#matchTelHangMade").attr("checked", false);
	}
	function match_team(pos, match, team) {
	    $.ajax({
		    url: "/matchTeamInfo?match="+match+"&pos="+pos+"&team="+team,
			success: function (data) {
			var info = data.split("\n");
			var nums = info[0].split(" ");
			$("#matchAutoScoreAtmp").val(nums[0]);
			$("#matchAutoScoreMade").val(nums[1]);
			$("#matchTelScoreAtmp").val(nums[2]);
			$("#matchTelScoreMade").val(nums[3]);
			$("#matchTelHangAtmp").val(nums[4]);
			$("#matchTelHangMade").attr("checked", nums[5] != '0');
			$("#matchAutoStart").val(num[6]);
			var pen = info[1].split("\\n");
			var penArea = $("#matchPenalities").empty();
			for(var i =0; i < pen.length; i++)
			    penArea.append('<li><input class="Penal" value="'+pen[i].replace(/\"/g, "\\\"")+'"/><li>');
			$("#matchNotes").val(info[2]);
		    }
		});
	}
	$("#matchSave").click(function () {
		$.ajax({
			url: "/matchTeamSave?match="+$("#matchNum").val()+"&team="+$("#"+$("#matchTeam").val()).html()+"&pos="+(function () {
				switch($("#matchTeam").val()) {
				case 'red1':
				    return 1;
				case 'red2':
				    return 2;
				case 'red3':
				    return 3;
				case 'blue1':
				    return 4;
				case 'blue2':
				    return 5;
				case 'blue3':
				    return 6;
				}
			    })()+"&autoAtemp="+$("#matchAutoScoreAtmp").val()
			    +"&autoMade="+$("#matchAutoScoreMade").val()
			    +"&autoStart="+$("#matchAutoStart").val()
			    +"&telAtemp="+$("#matchTelScoreAtmp").val()
			    +"&telMade="+$("#matchTelScoreMade").val()
			    +"&hangAtemp="+$("#matchTelHangAtmp").val()
			    +"&hangMade="+$("#matchTelHangMade").val()
		    });
	    });
	$("#matchNum").change(function () {
		match($(this).val()*1);
	    });
	$("#matchTeam").change(function () {
		var pos;
		switch($(this).val()) {
		case 'red1':
		    pos=1;
		    break;
		case 'red2':
		    pos=2;
		    break;
		case 'red3':
		    pos=3;
		    break;
		case 'blue1':
		    pos=4;
		    break;
		case 'blue2':
		    pos=5;
		    break;
		case 'blue3':
		    pos=6;
		    break;
		}
		match_team(pos, $("#matchNum").val()*1, $("#"+$(this).val()).html());
	    });
	$("#enterSave").click(function () {
		var data = $("#enterMatches").val().split("\n");
		for (var i =0; i < data.length; i++)
		    if(data[i])
			$.ajax({
				url: "/enterMatch?game="+data[i],
				    type: "GET",
				    succuss: function () {
				    
				}
			    });
	    });
	$("#matchAddPenalities").click(function () {
		$("#matchPenalities").append('<li><input class="Penal"/><li>');
	    });
    });


