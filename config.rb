# Require any additional compass plugins here.

# Set this to the root of your project when deployed:
http_path = "/"
css_dir = "/"
sass_dir = "/"
images_dir = "images"

# output_style = :expanded or :nested or :compact or :compressed
output_style = :expanded

relative_assets = true

# line_comments and debug_info can be activated by setting the environment
# flag to "development"
line_comments = (environment == :development) ? true : false

sass_options = {
  :debug_info => (environment == :development) ? true : false
}
