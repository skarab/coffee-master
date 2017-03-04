function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6421\" class=\"headerLeftMenuInActive\"><a id=\"aID6421\" href=\"#\" OnMouseOver=\"link('_dir','plugin0',this)\" class=\"leftMenuLinkHeadInActive\">plugin</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID943\" class=\"leftMenuInActive\"><a id=\"aID943\" href=\"#\" OnMouseOver=\"link('_class','Plugin39455',this)\" class=\"leftMenuLinkInActive\">Plugin</a></div>\n");
document.write("<div id=\"divID944\" class=\"leftMenuInActive\"><a id=\"aID944\" href=\"#\" OnMouseOver=\"link('_class','PluginAttachNodeUndo39455',this)\" class=\"leftMenuLinkInActive\">PluginAttachNodeUndo</a></div>\n");
document.write("<div id=\"divID945\" class=\"leftMenuInActive\"><a id=\"aID945\" href=\"#\" OnMouseOver=\"link('_class','PluginDetachNodeUndo39455',this)\" class=\"leftMenuLinkInActive\">PluginDetachNodeUndo</a></div>\n");
document.write("<div id=\"divID946\" class=\"leftMenuInActive\"><a id=\"aID946\" href=\"#\" OnMouseOver=\"link('_class','PluginNodeController39455',this)\" class=\"leftMenuLinkInActive\">PluginNodeController</a></div>\n");
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
