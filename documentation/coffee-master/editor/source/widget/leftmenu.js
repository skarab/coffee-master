function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6499\" class=\"headerLeftMenuInActive\"><a id=\"aID6499\" href=\"#\" OnMouseOver=\"link('_dir','widget0',this)\" class=\"leftMenuLinkHeadInActive\">widget</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6482\" class=\"leftMenuInActive\"><a id=\"aID6482\" href=\"#\" OnMouseOver=\"link('_dir','config_dialog/config_dialog0',this)\" class=\"leftMenuLinkInActive\">config_dialog</a></div>\n");
document.write("<div id=\"divID6484\" class=\"leftMenuInActive\"><a id=\"aID6484\" href=\"#\" OnMouseOver=\"link('_dir','debugger/debugger0',this)\" class=\"leftMenuLinkInActive\">debugger</a></div>\n");
document.write("<div id=\"divID6485\" class=\"leftMenuInActive\"><a id=\"aID6485\" href=\"#\" OnMouseOver=\"link('_dir','editor_frame/editor_frame0',this)\" class=\"leftMenuLinkInActive\">editor_frame</a></div>\n");
document.write("<div id=\"divID6487\" class=\"leftMenuInActive\"><a id=\"aID6487\" href=\"#\" OnMouseOver=\"link('_dir','explorer/explorer0',this)\" class=\"leftMenuLinkInActive\">explorer</a></div>\n");
document.write("<div id=\"divID6488\" class=\"leftMenuInActive\"><a id=\"aID6488\" href=\"#\" OnMouseOver=\"link('_dir','gizmo_controller/gizmo_controller0',this)\" class=\"leftMenuLinkInActive\">gizmo_controller</a></div>\n");
document.write("<div id=\"divID6489\" class=\"leftMenuInActive\"><a id=\"aID6489\" href=\"#\" OnMouseOver=\"link('_dir','mdi/mdi0',this)\" class=\"leftMenuLinkInActive\">mdi</a></div>\n");
document.write("<div id=\"divID6490\" class=\"leftMenuInActive\"><a id=\"aID6490\" href=\"#\" OnMouseOver=\"link('_dir','node_editor/node_editor0',this)\" class=\"leftMenuLinkInActive\">node_editor</a></div>\n");
document.write("<div id=\"divID6491\" class=\"leftMenuInActive\"><a id=\"aID6491\" href=\"#\" OnMouseOver=\"link('_dir','output/output0',this)\" class=\"leftMenuLinkInActive\">output</a></div>\n");
document.write("<div id=\"divID6492\" class=\"leftMenuInActive\"><a id=\"aID6492\" href=\"#\" OnMouseOver=\"link('_dir','package_importer/package_importer0',this)\" class=\"leftMenuLinkInActive\">package_importer</a></div>\n");
document.write("<div id=\"divID6493\" class=\"leftMenuInActive\"><a id=\"aID6493\" href=\"#\" OnMouseOver=\"link('_dir','project_browser/project_browser0',this)\" class=\"leftMenuLinkInActive\">project_browser</a></div>\n");
document.write("<div id=\"divID6495\" class=\"leftMenuInActive\"><a id=\"aID6495\" href=\"#\" OnMouseOver=\"link('_dir','project_manager/project_manager0',this)\" class=\"leftMenuLinkInActive\">project_manager</a></div>\n");
document.write("<div id=\"divID6496\" class=\"leftMenuInActive\"><a id=\"aID6496\" href=\"#\" OnMouseOver=\"link('_dir','properties/properties0',this)\" class=\"leftMenuLinkInActive\">properties</a></div>\n");
document.write("<div id=\"divID6497\" class=\"leftMenuInActive\"><a id=\"aID6497\" href=\"#\" OnMouseOver=\"link('_dir','selection_controller/selection_controller0',this)\" class=\"leftMenuLinkInActive\">selection_controller</a></div>\n");
document.write("<div id=\"divID6498\" class=\"leftMenuInActive\"><a id=\"aID6498\" href=\"#\" OnMouseOver=\"link('_dir','undo_controller/undo_controller0',this)\" class=\"leftMenuLinkInActive\">undo_controller</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
