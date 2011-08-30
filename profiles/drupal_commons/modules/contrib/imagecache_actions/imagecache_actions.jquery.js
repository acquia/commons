/* 
 * UI enhancements for the imagecache edit form
 */

if(Drupal.jsEnabled){
  $(document).ready(function(){
    // canvasactions_roundedcorners
    // check if independent corners are enabled and disable other fields
    canvasactions_roundedcorners_form_disable_fields();
    $(":checkbox#edit-data-independent-corners-set-independent-corners").change(function(){canvasactions_roundedcorners_form_disable_fields(); } );
  });
}


function canvasactions_roundedcorners_form_disable_fields(){
  // canvasactions_roundedcorners
  // check if independent corners are enabled and disable other fields
  if(!$(":checkbox#edit-data-independent-corners-set-independent-corners").attr("checked")){
    $("#independent-corners-set-wrapper .form-text").attr("disabled", true).addClass("disabled");
    $(":input#edit-data-radius").attr("disabled", false).removeClass("disabled");
  } else {
    $(":input#edit-data-radius").attr("disabled", true).addClass("disabled");
    $("#independent-corners-set-wrapper .form-text").attr("disabled", false).removeClass("disabled");
  }
}