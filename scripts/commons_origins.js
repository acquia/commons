(function ($) {
	$(document).ready(function() {

//		$.fn.textWidth = function(){
//		  var html_org = $(this).html();
//		  var html_calc = '<span>' + html_org + '</span>';
//		  $(this).html(html_calc);
//		  var width = $(this).find('span:first').width();
//		  $(this).html(html_org);
//		  return width;
//		};
	
//		var selectwidth = $('#edit-following option:selected').textWidth();
//		console.log(selectwidth);

		$('.views-exposed-widgets .form-select').change(function() {
			$('.views-exposed-widgets .views-submit-button').fadeIn(300);
		});

	//placeholder functionality	
		$('.view-id-commons_homepage_content .views-row-1 article h1').append("<div class='tag new'></div><div class='tag featured'></div>");
		$('#block-system-main-menu .menu-depth-1 a').append("<div class='arrow'></div>")
	});

})(jQuery);