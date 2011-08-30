(function ($){
	$('document').ready(function () {
		var $defaultText = $('input[name=search_theme_form]').val(); // get default text (Search...)
		
		$('input[name=search_theme_form]').focus(function(){ // clear search box when user clicks on it
			if ($(this).val() == $defaultText){
				$(this).val("");
			}// end if
		});// end function
		
		$('input[name=search_theme_form]').blur(function(){ // reset text to default if the user does not input any text and clicks on everything else
			if ($(this).val() == ""){
				$(this).val($defaultText);
			}// end if
		});// end function
		
	});// end document
})(jQuery);