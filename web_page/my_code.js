
///////////////////
// start my code //
///////////////////

var mode;

$(function () {
	mode = $("#mode").change(function () {
		// the mode of the page changes
		mode = $(this).val();
		switch(mode) {
		case "chose":
		    // you really fail
		    return; // what can I do
		case "enterList": // enter the list of matches
		    return alert('working');
		case "scoreMatch": // scoring the match
		    return;
		}
	    }).val();;
    });
