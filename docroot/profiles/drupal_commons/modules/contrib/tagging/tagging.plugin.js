// $Id: tagging.plugin.js,v 1.12.2.6 2010/10/17 10:23:24 eugenmayer Exp $
/**
 * @author Eugen Mayer (http://kontextwork.de)
 * @Copyright 2010 KontextWork
 */
(function($) {
  $.fn.tagging = function() {
    return this.each( function(){
      // **************** Init *****************/
      var context = get_context($(this).attr('class'));
      
      if(context === null) {
        alert('cant initialize tagging-widget: "'+$(this).attr('id')+'"..did you forget the "taggig-widget-$CONTEXT" class?');
        return;
      }
      // Our containers.
      var input_sel = '.tagging-widget-input-'+context;
      var button_sel = '.tagging-button-'+context;
      var wrapper_sel = '.tagging-curtags-wrapper-'+context;
      var suggestions_wrapper_sel = '.tagging-suggestions-wrapper-'+context;
      var target_sel = '.tagging-widget-target-'+context;
      var suggest_class = 'tagging-suggest-tag';
      var tag_class = 'tagging-tag';
      var suggest_sel = '.'+suggest_class;
      var tag_sel =  '.'+tag_class;

      // Lets set all things up.
      bind_taglist_events();
      bind_button();
      update_tags();
      bind_enter();
      check_dublicates();

      $(input_sel).val('');
      $(this).addClass('tagging-processed');
      // **************** Helper methods *****************/
      /*
      * Adds a tag to the visual list and to the hidden input field (target).
      */
      function add_tag(tag, autoupdate) {
        tag = Drupal.checkPlain(tag);
        $(wrapper_sel).append("<span class='"+tag_class+"'>"+tag+"</span>");
        if(autoupdate) {
          update_tags();
        }
      }

      /*
      * Removes a tag out of the visual list and out of the hidden input field (target).
      */
      function remove_tag(e) {
        $(e).remove();
        unbind_taglist_events();
        update_tags();
        bind_taglist_events();
        reshow_suggestion_if_exists($(e).text());
      }

      /*
      * Hides a tag out of the visual list. Suggestions need this to restore later
      */
      function hide_tag(e) {
        $(e).hide();
        unbind_taglist_events();
        update_tags();
        bind_taglist_events();
      }
      
      /*
      * Updates the hidden input textfield with current tags.
      * We do so, that we later can pass the tags to the taxonomy validators
      * and dont have to fight with module weights.
      */
      function update_tags() {
        var tags = new Array();
        $(wrapper_sel+' '+tag_sel).each( function () {
          tags.push($(this).text());
        });
        $(target_sel).val(tags.join(','));
      }

      /*
      * Checks, if the tag already exists. Lets avoid the dublicates
      * we have seen in the past. We dont tell the use anything, we
      * just do as we would have added it, as the user expects to have the tag
      * added, no matter its there or not.
      */
      function tag_exists(tag) {
        var tag = $.trim(tag.toLowerCase());
        var found = false;
        $(wrapper_sel+' '+tag_sel).each(function() {
          if($.trim($(this).text().toLowerCase()) == tag) {
            found = true;
            return;
          }
        });
        return found;
      }

      /*
      * If a tag is removed from the tag list, we check here if it was a suggestion before
      * if yes, we show it again in the suggestion list
      */
      function reshow_suggestion_if_exists(tag) {
        $(suggestions_wrapper_sel+' '+suggest_sel+':hidden').each(function() {
          if($(this).text() === tag) {
            $(this).show();
          }
        });
      }

      /*
      * Adds the button to the inputfield. Actuall the button is optional
      * as we also add (primary) by pressing enter.
      */
      function bind_button() {
        $(button_sel).bind('click',function() {
          tags = $(input_sel).not('.tag-processed').val().split(',');
          $.each(tags, function(i, tag) {
            tag = jQuery.trim(tag);
            if (tag != '' && !tag_exists(tag)) {
              add_tag(tag, false);
            }
          });
          $(input_sel).val('');
          update_tags();
          bind_taglist_events();
          return false;
        });
      }

      /*
      * Event for keypress on the input field of the tagging-widget.
      */
      function bind_enter() {
        if ($.browser.mozilla || $.browser.opera) {
          $(input_sel).bind('keypress',check_enter);
        }
        else {
          $(input_sel).bind('keydown',check_enter);
        }
      }
      
      /*
      * Checks, if enter is pressed. If yes, close the autocompletition
      * use the selected item and add it to the tag-list.
      */
      function check_enter(event) {
        var key = event.which;
        if (key == 13) {
          $('#autocomplete').each(function() {
            this.owner.hidePopup();
          });
          $(button_sel).trigger('click');
          event.preventDefault();
          return false;
        }
        return true;
      }

      /*
      * Check for dupblicates in suggestions and allready assgined tags.
      * Hide suggestions on match.
      */
      function check_dublicates(){
        // TODO: Using this optimized selector somehow interfers with the
        // fckeditor as a module. Yet no idea what happens.
        // sel = suggestions_wrapper_sel + ' div' + suggest_sel + ":visble";

        // Fallback selector
        sel = suggestions_wrapper_sel + ' span' + suggest_sel;
        $(sel).each(function(){
          if( tag_exists($(this).text()) ) {
            $(this).hide();
          }
        });
      }
      
      /*
      * Adds the remove-tag methods to the tags in the wrapper.
      */
      function bind_taglist_events() {
        $(wrapper_sel+' span'+tag_sel+':not(span.processed)').each(function() {
          $(this).addClass('processed');
          // We use non anonymuos binds to be properly able to unbind them.
          $(this).bind('click',remove_tag_click);
        });


        // For suggestion, we only hide tags. When those tags are remove from the tag
        // list, we can simply check for the existence and show them again
        $(suggestions_wrapper_sel+' span'+suggest_sel+':not(span.processed)').each(function() {
          // We use non anonymuos binds to be able to properly unbind them
          $(this).addClass('processed');
          $(this).bind('click',add_suggestion_tag_click);
        });
      }

      /*
      * Click event for a suggested tag.
      */
      function add_suggestion_tag_click () {
        $(this).addClass('processed');
        tag = $(this).text();
        // skip, if this tag is already assigned
        if (tag_exists(tag)) {
          return false;
        }
        add_tag(tag);
        hide_tag(this);
        return false;
      }

      /*
      * Click event for a tag.
      */
      function remove_tag_click() {
        remove_tag(this); return false;
      }

      /*
      * During updating of the tags, we unbind the events to avoid
      * sideffects.
      */
      function unbind_taglist_events() {
        $(wrapper_sel+' '+tag_sel).each(function() {
            $(this).removeClass('processed');
            $(this).unbind('click',remove_tag_click);
            return false;
          }
        );

        $(suggestions_wrapper_sel+' '+suggest_sel).each(function() {
            $(this).removeClass('processed');
            $(this).unbind('click',add_suggestion_tag_click);
            return false;
          }
        );
      }

      /*
      * Extracts the content ID - for drupal thats the VID.
      * This is extracted from the tagging-widget-XX class
      * if the input element, which actuall has the tagging-widget class.
      */
      function get_context(classes) {
        context = null;
        $(classes.split(' ')).each(function(){
          match = this.match(/tagging[-]widget[-]input[-](\d+)/i);
          if (match != null) {
            context =  match[1];
          }
        });
        return context;
      }
    }
    );
  }
})(jQuery);
