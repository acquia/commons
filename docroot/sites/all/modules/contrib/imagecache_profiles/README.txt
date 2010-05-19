; $Id: README.txt,v 1.3.2.3 2010/02/22 16:39:25 andypost Exp $
Imagecache_Profiles module allows you to set user profile pictures that are consistent throughout your site and allows avatars on the user profile pages to be a different size.

- Download and enable the ImageCache module
  - create a new ImageCache preset with the following settings
    - preset namespace: user_image_default
      - select "Add Scale and Crop" from the New Actions fieldgroup
        - set width and height to 100
        - Update Actions
    - preset namespace: user_image_large
      - select "Add Scale and Crop" from the New Actions fieldgroup
        - set width and height to 200
        - Update Actions

- Download and enable the ImageCache_Profiles module as usual
  - Enable user pictures at admin/user/settings
    - if setting a default picture it should use a relative url path (ex. sites/default/files/default-picture.png)
    - set picture maximum dimensions to 1600x1400
    - set picture maximum file size to 1024
    - set your picture guidelines text to: "Photo must be larger than 200x200 pixels." To prevent upscaling, these dimensions should be the dimensions of your largest preset.
    - select the ImageCache preset to set the user picture size on a user's profile page
    - select the ImageCache preset to set the user picture size within comments
    - select the ImageCache preset to set the default user picture size throughout the site
    - set picture minimum width in pixels: 200
    - set picture minimum height in pixels: 200
      - To prevent upscaling, these dimensions should be the dimensions of your largest preset.
    - save configuration

WARNING! Do not use numeric identifiers for ImageCache presets!
