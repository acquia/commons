/**
 * The heartbeat object.
 */
Drupal.heartbeat = Drupal.heartbeat || {};

Drupal.heartbeat.moreLink = null;

/**
 * wait().
 *   Function that shows throbber while waiting a response.
 */
Drupal.heartbeat.wait = function(element, parentSelector) {

  // We wait for a server response and show a throbber 
  // by adding the class heartbeat-messages-waiting.
  Drupal.heartbeat.moreLink = $(element).parents(parentSelector);
  // Disable double-clicking.
  if (Drupal.heartbeat.moreLink.is('.heartbeat-messages-waiting')) {      
    return false;
  }
  Drupal.heartbeat.moreLink.addClass('heartbeat-messages-waiting');
  
}

/**
 * doneWaiting().
 *   Function that is triggered if waiting period is over, to start
 *   normal behavior again.
 */
Drupal.heartbeat.doneWaiting = function() {
  Drupal.heartbeat.moreLink.removeClass('heartbeat-messages-waiting');
}

/**
 * getOlderMessages().
 *   Fetch older messages with ajax.
 */
Drupal.heartbeat.getOlderMessages = function(element, page) {
  Drupal.heartbeat.wait(element, '.heartbeat-more-messages-wrapper');
  $.post(element.href, {block: page ? 0 : 1, ajax: 1}, Drupal.heartbeat.appendMessages);
}

/**
 * pollMessages().
 *   Function that checks and fetches newer messages to the
 *   current stream.
 */
Drupal.heartbeat.pollMessages = function() {

  if ($('.heartbeat-stream').length > 0) {

    var href = Drupal.settings.basePath + 'heartbeat/js/poll';
    var stream = $('.heartbeat-stream').attr('id').replace("heartbeat-stream-", "");    
    var uaids = new Array();
    var beats = $('.heartbeat-stream .beat-item');
    var firstUaid = 0;
    
    if (beats.length > 0) {    
      firstUaid = $(beats.get(0)).attr('id').replace("beat-item-", "");
      
      beats.each(function(i) {  
        var uaid = parseInt($(this).attr('id').replace("beat-item-", ""));
        uaids.push(uaid);
      });
    }
    
    if (firstUaid) {
      $.post(href, {latestUaid: firstUaid, language: Drupal.settings.heartbeat_language, stream: stream, uaids: uaids.join(',')}, Drupal.heartbeat.prependMessages);
    }
  }
}

/**
 * appendMessages().
 *   Function that appends older messages to the stream.
 */
Drupal.heartbeat.appendMessages = function(data) {
  
  var result = Drupal.parseJson(data);
  
  var wrapper = Drupal.heartbeat.moreLink.parents('.heartbeat-messages-wrapper');
  Drupal.heartbeat.moreLink.remove();
  wrapper.append(result['data']);
  Drupal.heartbeat.doneWaiting();
    
  // Reattach behaviors for new added html
  Drupal.attachBehaviors($('.heartbeat-messages-wrapper'));
  
}

/**
 * prependMessages().
 *   Append messages to the front of the stream. This done for newer 
 *   messages, often with the auto poller.
 */
Drupal.heartbeat.prependMessages = function(data) {

  var result = Drupal.parseJson(data);
  
  if (result['data'] != '') {
  
    // Append the messages
    $('.heartbeat-messages-wrapper').prepend(result['data']);
  
    // Update the times in the stream
    var time_updates = result['time_updates'];
    for (uaid in time_updates) {
      $('#beat-item-' + uaid).find('.heartbeat_times').text(time_updates[uaid]);
    }
    
    // Reattach behaviors for new added html
    Drupal.attachBehaviors($('.heartbeat-messages-wrapper'));
  }
}

/**
 * Document onReady().
 */
$(document).ready(function() {

  if (Drupal.settings.heartbeatPollNewerMessages > 0) {
    var interval = Drupal.settings.heartbeatPollNewerMessages * 1000;
    var poll = setInterval('Drupal.heartbeat.pollMessages()', interval);
  }
  
});