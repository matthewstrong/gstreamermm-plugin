#include "GstPlugin.h"
#include "TestPlugin.h"

#include <gstreamermm.h>
#include <gstreamermm/private/pluginfeature_p.h>
#include <gstreamermm/private/plugin_p.h>
#include <gstreamermm/private/elementfactory_p.h>
#include <gstreamermm/private/basetransform_p.h>

using Glib::RefPtr;

GST_DEBUG_CATEGORY_STATIC (gst_plugin_template_debug);
#define GST_CAT_DEFAULT gst_plugin_template_debug

static void wrap_init(void);

/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
gboolean
gst_cpptest_plugin_init (GstPlugin * plugin)
{
    /* debug category for fltering log messages
    *
    * exchange the string 'Template plugin' with your description
    */
    GST_DEBUG_CATEGORY_INIT (gst_plugin_template_debug, "plugin",
        0, "Template plugin");

    wrap_init();
    RefPtr<Gst::Plugin> plugin_wrapped = Glib::wrap (plugin, true);

    gboolean ret = TRUE;
    ret &= DerivedFromBaseTransform::register_element (plugin_wrapped);

    return ret;
}

/* PACKAGE: this is usually set by autotools depending on some _INIT macro
 * in configure.ac and then written into and defined in config.h, but we can
 * just set it ourselves here in case someone doesn't use autotools to
 * compile this code. GST_PLUGIN_DEFINE needs PACKAGE to be defined.
 */
#ifndef PACKAGE
#define PACKAGE "gst-cpp-plugins"
#endif

/* gstreamer looks for this structure to register plugins
 *
 * exchange the string 'Template plugin' with your plugin description
 */
GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    cpptest,
    "C++ Test Plugin",
    gst_cpptest_plugin_init,
    PLUGIN_VERSION,
    "GPL",
    "GStreamer",
    "http://example.com/"
)

static void wrap_init(void)
{
    Glib::init();

    Glib::wrap_register(gst_object_get_type(), &Gst::Object_Class::wrap_new);
    Glib::wrap_register(gst_element_get_type(), &Gst::Element_Class::wrap_new);
    Glib::wrap_register(gst_element_factory_get_type(), &Gst::ElementFactory_Class::wrap_new);
    Glib::wrap_register(gst_plugin_get_type(), &Gst::Plugin_Class::wrap_new);
    Glib::wrap_register(gst_plugin_feature_get_type(), &Gst::PluginFeature_Class::wrap_new);
    Glib::wrap_register(gst_base_transform_get_type(), &Gst::BaseTransform_Class::wrap_new);

    Gst::Object::get_type();
    Gst::Element::get_type();
    Gst::ElementFactory::get_type();
    Gst::Plugin::get_type();
    Gst::PluginFeature::get_type();
    Gst::BaseTransform::get_type();
}
