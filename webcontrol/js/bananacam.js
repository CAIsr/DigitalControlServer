properties = [
    ["iso", "ISO"],
    ["whitebalance", "White Balance"],
    ["imagequality", "Image Quality"],
    ["f-number", "F Number"],
    ["shutterspeed", "Shutter Speed"],
    ["imagesize", "Image Size"],
    ["500e", "Mode"],
    ["shootingspeed", "Shooting speed"]
];

property_list_camera = [];

function ajax_send(url)
{
    
    $.get(url, function(data)
	  {
	      console.log(data);
	      var i = 0;
	      var split_msg = data.split("\n");
	      
	      while (i < split_msg.length)
		  {
		      var split_list = split_msg[i].split("|");
		      if (split_list[0] == "1") // OK
			  {
			      $("#logspace").append('<tr class="success"><td>' + split_list[1] + '</td></tr><br />');
			      $("#val-" + split_list[2]).text(split_list[3]);
			  }
		      if (split_list[0] == "2") // KO
			  $("#logspace").append('<tr class="error"><td>' + split_list[1] + '</td></tr><br />');
		      if (split_list[0] == "4") // WRONG_COMMAND
			  $("#logspace").append('<tr class="error"><td>' + split_list[1] + '</td></tr><br />');
		      if (split_list[0] == "8") // BAD_PARAMETERS
			  $("#logspace").append('<tr class="warning"><td>' + split_list[1] + '</td></tr><br />');
		      if (split_list[0] == "16") // WAIT_RESPONSE
			  $("#logspace").append('<tr class="info"><td>' + split_list[1] + '</td></tr><br />');
		      if (split_list[0] == "32") // COMPLETE
			  {
			      $("#logspace").append('<tr class="success"><td>' + split_list[1] + '</td></tr><br />');
			      $("#val-" + split_list[2]).text(split_list[3]);
			  }
		      if (split_list[0] == "64") // EXEC
			  $("#logspace").append('<tr><td>' + split_list[1] + '</td></tr><br />');
		      if (split_list[0] == "128") // INFO
			  $("#logspace").append('<tr class="info"><td>' + split_list[1] + '</td></tr><br />');
		      if (split_list[0] == "256") // VALUE
			  $("#logspace").append('<tr>' + split_list[1] + '</td></tr><br />');
		      i++;
		  }
	      return false;	
	  });
}

function check_properties(property_list, property)
{
    var i = 0;
    
    while (i < property_list.length)
    {
	if (property == property_list[i][0])
	    return (1);
	i++;
    }
    
    return (0);
}

function is_camera_property(property, propert_list_camera)
{
    var i = 0;
    
    while (i < property_list_camera.length)
    {
	if (property == property_list_camera[i][0])
	    return (1);
	i++;
    }
    return (0);
}

function get_index_property(propert_list_camera, property)
{
    var i = 0;
    
    while (i < property_list_camera.length)
    {
	if (property == property_list_camera[i][0])
	    return (i);
	i++;
    }
    return (-1);
}

function set_property_html(url, property_list, propert_list_camera)
{
    var i = 0;
    /*
     **
     **  Activated options only defined by the global properties array
     **
     **
      while (i < property_list.length)
    {
	if (is_camera_property(property_list[i][0], property_list_camera))
	{
	    var text = '<div class="span2"> <div class="dropdown"> <a class="dropdown-toggle btn btn-block" id=\"drop-' + property_list[i][0] + '" role="button" data-toggle="dropdown" href="#">' + property_list[i][1] + ' <b class="caret"></b></a><ul class="dropdown-menu" id="' + property_list[i][0] + '" role="menu" aria-labelledby="drop-' + property_list[i][0] + '"></ul></div></div>';

	    $("#container").append(text);
	
	    var j = 0;
	    var balise =  "ul#" + property_list[i][0];
	    console.log(property_list[i]);
	    var index = get_index_property(property_list_camera, property_list[i][0]);
	    if (index != -1)
	    {
		while (j < property_list_camera[index][2].length)
		{
		    $(balise).append('<li role="presentation"><a href="' + url + 'BananaCam/?=64&' + property_list[i][0] + '&setting_' + property_list[i][0] +'&' + property_list_camera[index][2][j] + '" onclick="ajax_send(this); return false;">' + property_list_camera[index][2][j] + '</a></li>');
		    j++;
		}
	    }
	    
	}
	i++;
    }
*/
      /*
      **
      **  All the camera options.
      **
      */

    i = 0;
    var elem = 1;
    var sub = 0;
    var k = 0;
    var loaded_config = new Array();
    $("#container").append('<br /><div class="row-fluid" id="subcontainer' + sub + '">');
    while (i < property_list_camera.length)
    {
	var ronly = (property_list_camera[i][2] == 1 ? ' <span class="label label-important">Readonly</span>' : '');

	if (property_list_camera[i][1] == "radio")
	{
	    var text = '<div class="span4"> <div class="dropdown"> <a class="dropdown-toggle btn btn-block" id=\"drop-' + property_list_camera[i][0] + '" role="button" data-toggle="dropdown" href="#"><div class="row-fluid" id="row-' + property_list_camera[i][0] + '"><div class="span8 text-left">' + ronly + "  " + property_list_camera[i][4] + ' <b class="caret"></b></div><div class="span4 text-right"><span id="val-' + property_list_camera[i][0] + '" class="label">' + property_list_camera[i][5] + '</span></div></div></a><ul class="dropdown-menu" id="' + property_list_camera[i][0] + '" role="menu" aria-labelledby="drop-' + property_list_camera[i][0] + '"></ul></div></div>';
	    
	    $("#subcontainer" + sub).append(text);
	    
	    var j = 0;
	    var balise =  "ul#" + property_list_camera[i][0];
	    while (j < property_list_camera[i][3].length)
	    {
		$(balise).append('<li role="presentation"><a href="' + url + 'BananaCam/?=64&' + property_list_camera[i][0] + '&setting_' + property_list_camera[i][0] +'&' + property_list_camera[i][3][j] + '" onclick="ajax_send(this); return false;">' + property_list_camera[i][3][j] + '</a></li>');
		j++;
	    }
	    elem++;
	    if (elem % 3 == 0)
		{
		    sub++;
		    if (elem > 0)
			$("#container").append('</div><br /><div class="row-fluid" id="subcontainer' + sub + '">');
		    else
			$("#container").append('<br /><div class="row-fluid" id="subcontainer' + sub + '">');
		}
	    loaded_config[k] = property_list_camera[i][0];
	    k++;
	}
	else if (property_list_camera[i][1] == "range")
	{	    
	    var balise =  "ul#" + property_list_camera[i][0];
	    var start = parseFloat(propert_list_camera[i][3][0]);
	    var end = parseFloat(propert_list_camera[i][3][1]);
	    var step = parseFloat(propert_list_camera[i][3][2]);
	    
	    if ((end - start) / step < 200 && step > 0)
	    {
		var text = '<div class="span4"> <div class="dropdown"> <a class="dropdown-toggle btn btn-block" id=\"drop-' + property_list_camera[i][0] + '" role="button" data-toggle="dropdown" href="#"><div class="row-fluid" id="row-' + property_list_camera[i][0] + '"><div class="span8 text-left">' + ronly + "  " + property_list_camera[i][4] + ' <b class="caret"></b></div><div class="span4 text-right"><span id="val-' + property_list_camera[i][0] + '" class="label">' + property_list_camera[i][5] + '</span></div></div></a><ul class="dropdown-menu" id="' + property_list_camera[i][0] + '" role="menu" aria-labelledby="drop-' + property_list_camera[i][0] + '"></ul></div></div>';
	    
		$("#subcontainer" + sub).append(text);

		while (start <= end)
		{
		    $(balise).append('<li role="presentation"><a href="' + url + 'BananaCam/?=64&' + property_list_camera[i][0] + '&setting_' + property_list_camera[i][0] +'&' + start + '" onclick="ajax_send(this); return false;">' + start + '</a></li>');
		    start += step;
		}
		elem++;
		if (elem % 3 == 0)
		{
		    sub++;
		    if (elem > 0)
			$("#container").append('</div><br /><div class="row-fluid" id="subcontainer' + sub + '">');
		    else
			$("#container").append('<br /><div class="row-fluid" id="subcontainer' + sub + '">');
		}
		loaded_config[k] = property_list_camera[i][0];
		k++;
	    }
	}
	i++;
    }
    $("#main-container").fadeIn("slow");
    spinner.stop();
    $("#main-container").fadeIn("slow");

//    get_value_loaded_config(url, loaded_config);
    return (0);
}

var lenght_init = 0;
var count_init = 0;

function get_value_loaded_config(url, loaded_config)
{
    var i = 0;
    lenght_init = loaded_config.length;
    while (i < loaded_config.length)
	{
	    $.get(url + "BananaCam/?=64&get_" + loaded_config[i] + "&getting_" + loaded_config[i] + "&NULL", function(data) {
		    var data_split = data.split("|");
		    $("#row-" + data_split[2]).append('<div class="span4 text-right"><span id="val-' + data_split[2] + '" class="label">' + data_split[3] + '</span></div>');
		    count_init++;
		    if (lenght_init == count_init)
			{
			    $("#loader_spinner").fadeOut("fast");
			    spinner.stop();
			    $("#main-container").fadeIn("slow");
			}
		});
	    i++;
	}
}

function load_config()
{
    var url = window.location.href;
    var capture_href = $("#capture_button a").attr("href");
    var final_link = url + capture_href;

    console.log(final_link);

    $("#capture_button a").attr("href", final_link);

    var final_link = url + $("#autofocus_button a").attr("href");

    $("#autofocus_button a").attr("href", final_link);

    $.get(url + "BananaCam/?=64&get_cameramodel&getting_camera_model&null", function(data) {
	    data_split = data.split("|");
	    $("#info-cam").append('<tr><td>Name</td><td>' + data_split[3] + '</td></tr>');
	});
    $.get(url + "BananaCam/?=64&get_manufacturer&getting_camera_model&null", function(data) {
	    data_split = data.split("|");
	    $("#info-cam").append('<tr><td>Manifacturer</td><td>' + data_split[3] + '</td></tr>');
	    $("#info-cam").append('<tr class="success"><td>Connected</td><td>OK</td></tr>');
	});
    $.get(url + "BananaCam/?=64&get_fullconfig&getting_full_conf&null", function(data) {
    
    var array_info = data.split("\n");
    var i = 0;
    while (i < array_info.length)
	{
	    var command = array_info[i].split("=>");
	    if (command[0] != "")
	    {
		var options_type = command[1].split("#");
		var options = options_type[4].split("|");
		
		var prop_array = new Array();
		prop_array[0] = command[0];      // command
		prop_array[1] = options_type[2]; // type
		prop_array[2] = options_type[1]; // ronly
		prop_array[3] = options;         // options
		prop_array[4] = options_type[0]; // label
		prop_array[5] = options_type[3]; // initial value

		property_list_camera[i] = prop_array;
	    }
	    i++;
	}
	set_property_html(url, properties, property_list_camera)
    });
}

var opts = {
    lines: 7, // The number of lines to draw
    length: 23, // The length of each line
    width: 22, // The line thickness
    radius: 18, // The radius of the inner circle
    corners: 1, // Corner roundness (0..1)
    rotate: 18, // The rotation offset
    direction: 1, // 1: clockwise, -1: counterclockwise
    color: '#ff0000', // #rgb or #rrggbb
    speed: 1.2, // Rounds per second
    trail: 100, // Afterglow percentage
    shadow: false, // Whether to render a shadow
    hwaccel: false, // Whether to use hardware acceleration
    className: 'spinner', // The CSS class to assign to the spinner
    zIndex: 2e9, // The z-index (defaults to 2000000000)
    top: 'auto', // Top position relative to parent in px
    left: 'auto' // Left position relative to parent in px
};

var target = document.getElementById('loader_spinner');
var spinner = new Spinner(opts);

$(function() {
    spinner.spin(target);
    load_config();
});