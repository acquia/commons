=======================================================
Additional actions for imagecache processing - a bundle
=======================================================
by dman http://coders.co.nz

Not all actions are ported to imageMagick yet, most are GD only. 
Please have a go if you understand imageMagick syntax!

Some actions are incredibly inefficient. The transparency effects may load
a whole image into memory and do bitwise operations on each pixel. This is
impractical on limited hosts. Take care.

Not all the modules in this package need to be enabled, 
just choose the ones you want.

The new actions should become available when you edit an imagecache preset
in the 'new action' drop-down underneath /admin/build/imagecache/{preset}

===============
TROUBLESHOOTING
===============
If actions don't seem to be showing up, it may be because of some heavy caching
the admin utility does.

- Visit /admin/build/modules.
- DISABLE one of the imagcache presets
- Visit /admin/build/modules/uninstall
- UNINSTALL that preset
- Then re-enable it!

That will shake up the system enough to recognize the new action.