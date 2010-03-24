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
	}
	function match_team(team) {
	    
	}
	$("#matchSave").click(function () {
		
	    });
	$("#matchNum").change(function () {
		match($(this).val()*1);
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


