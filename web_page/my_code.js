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
		return alert('working');
	    case "scoreMatch": // scoring the match
		$("#matchScouting").show();
		return;
	    }
	}
	
	mode_change.apply($("#mode")); // I think there is something in the jquery api that will do this
	$("#mode").change(mode_change);
	function match (number) {
	    
	}
	function match_team(team) {
	    
	}
	$("#matchNum").change(function () {
		match($(this).val()*1);
	    });
    });


