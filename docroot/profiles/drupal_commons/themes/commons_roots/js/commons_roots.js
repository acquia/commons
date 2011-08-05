function commons_search_site(){
  $('#search .search_submit').trigger('click');
}

function commons_search_user(){
  window.location = "/search/user/" + $('#search .search-input').val();
}

function commons_search_group(){
  window.location = commons_search_group_action + '?keys=' + $('#search .search-input').val();
}

var commons_search_group_action;

$(document).ready(function(){
  var commons_search_links = '<li class="commons-search-site"><a href="javascript:commons_search_site();">Site</a></li><li class="commons-search-user"><a href="javascript:commons_search_user();">People</a></li>';
  
  if($('#views-exposed-form-og-search-default').length > 0){
    commons_search_group_action = $('#views-exposed-form-og-search-default').attr('action');
    commons_search_links = commons_search_links + '<li class="commons-search-group"><a href="javascript:commons_search_group();">' + $('h1.title').text() + '</a></li>';
  }
  
  $('#search').append('<ul id="commons-search-options">' + commons_search_links + '</ul>');
  
  $('#commons-search-options').hover(function(){
    $('.commons-search-user, .commons-search-group').show();
  },function(){
    $('.commons-search-user, .commons-search-group').hide();
  });
});
