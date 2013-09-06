# Require any additional compass plugins here.

http_path = "/"
css_dir = "css"
sass_dir = "sass"
images_dir = "images"
javascripts_dir = "scripts"

# output_style = :expanded or :nested or :compact or :compressed
output_style = :expanded

relative_assets = true
 
# line_comments and debug_info can be activated by setting the environment
# flag to "development"
line_comments = (environment == :development) ? true : false

sass_options = {
  :debug_info => (environment == :development) ? true : false
}
