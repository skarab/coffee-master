function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6461\" class=\"headerLeftMenuInActive\"><a id=\"aID6461\" href=\"#\" OnMouseOver=\"link('_dir','widget0',this)\" class=\"leftMenuLinkHeadInActive\">widget</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6443\" class=\"leftMenuInActive\"><a id=\"aID6443\" href=\"#\" OnMouseOver=\"link('_dir','button/button0',this)\" class=\"leftMenuLinkInActive\">button</a></div>\n");
document.write("<div id=\"divID6444\" class=\"leftMenuInActive\"><a id=\"aID6444\" href=\"#\" OnMouseOver=\"link('_dir','check_box/check_box0',this)\" class=\"leftMenuLinkInActive\">check_box</a></div>\n");
document.write("<div id=\"divID6445\" class=\"leftMenuInActive\"><a id=\"aID6445\" href=\"#\" OnMouseOver=\"link('_dir','combo_box/combo_box0',this)\" class=\"leftMenuLinkInActive\">combo_box</a></div>\n");
document.write("<div id=\"divID6446\" class=\"leftMenuInActive\"><a id=\"aID6446\" href=\"#\" OnMouseOver=\"link('_dir','dialog/dialog0',this)\" class=\"leftMenuLinkInActive\">dialog</a></div>\n");
document.write("<div id=\"divID6447\" class=\"leftMenuInActive\"><a id=\"aID6447\" href=\"#\" OnMouseOver=\"link('_dir','edit_box/edit_box0',this)\" class=\"leftMenuLinkInActive\">edit_box</a></div>\n");
document.write("<div id=\"divID6448\" class=\"leftMenuInActive\"><a id=\"aID6448\" href=\"#\" OnMouseOver=\"link('_dir','group/group0',this)\" class=\"leftMenuLinkInActive\">group</a></div>\n");
document.write("<div id=\"divID6449\" class=\"leftMenuInActive\"><a id=\"aID6449\" href=\"#\" OnMouseOver=\"link('_dir','image/image0',this)\" class=\"leftMenuLinkInActive\">image</a></div>\n");
document.write("<div id=\"divID6450\" class=\"leftMenuInActive\"><a id=\"aID6450\" href=\"#\" OnMouseOver=\"link('_dir','label/label0',this)\" class=\"leftMenuLinkInActive\">label</a></div>\n");
document.write("<div id=\"divID6451\" class=\"leftMenuInActive\"><a id=\"aID6451\" href=\"#\" OnMouseOver=\"link('_dir','list_view/list_view0',this)\" class=\"leftMenuLinkInActive\">list_view</a></div>\n");
document.write("<div id=\"divID6452\" class=\"leftMenuInActive\"><a id=\"aID6452\" href=\"#\" OnMouseOver=\"link('_dir','menu/menu0',this)\" class=\"leftMenuLinkInActive\">menu</a></div>\n");
document.write("<div id=\"divID6453\" class=\"leftMenuInActive\"><a id=\"aID6453\" href=\"#\" OnMouseOver=\"link('_dir','progress_bar/progress_bar0',this)\" class=\"leftMenuLinkInActive\">progress_bar</a></div>\n");
document.write("<div id=\"divID6454\" class=\"leftMenuInActive\"><a id=\"aID6454\" href=\"#\" OnMouseOver=\"link('_dir','scroll_bar/scroll_bar0',this)\" class=\"leftMenuLinkInActive\">scroll_bar</a></div>\n");
document.write("<div id=\"divID6455\" class=\"leftMenuInActive\"><a id=\"aID6455\" href=\"#\" OnMouseOver=\"link('_dir','tab_control/tab_control0',this)\" class=\"leftMenuLinkInActive\">tab_control</a></div>\n");
document.write("<div id=\"divID6456\" class=\"leftMenuInActive\"><a id=\"aID6456\" href=\"#\" OnMouseOver=\"link('_dir','text_box/text_box0',this)\" class=\"leftMenuLinkInActive\">text_box</a></div>\n");
document.write("<div id=\"divID6457\" class=\"leftMenuInActive\"><a id=\"aID6457\" href=\"#\" OnMouseOver=\"link('_dir','tool_bar/tool_bar0',this)\" class=\"leftMenuLinkInActive\">tool_bar</a></div>\n");
document.write("<div id=\"divID6458\" class=\"leftMenuInActive\"><a id=\"aID6458\" href=\"#\" OnMouseOver=\"link('_dir','tool_tip/tool_tip0',this)\" class=\"leftMenuLinkInActive\">tool_tip</a></div>\n");
document.write("<div id=\"divID6459\" class=\"leftMenuInActive\"><a id=\"aID6459\" href=\"#\" OnMouseOver=\"link('_dir','tree_control/tree_control0',this)\" class=\"leftMenuLinkInActive\">tree_control</a></div>\n");
document.write("<div id=\"divID6460\" class=\"leftMenuInActive\"><a id=\"aID6460\" href=\"#\" OnMouseOver=\"link('_dir','view_control/view_control0',this)\" class=\"leftMenuLinkInActive\">view_control</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1038\" class=\"leftMenuInActive\"><a id=\"aID1038\" href=\"#\" OnMouseOver=\"link('_class','Widget45101',this)\" class=\"leftMenuLinkInActive\">Widget</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6253\" class=\"leftMenuInActive\"><a id=\"aID6253\" href=\"#\" OnMouseOver=\"link('_member','EVENT1141535755',this)\" class=\"leftMenuLinkInActive\">EVENT</a></div>\n");
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
