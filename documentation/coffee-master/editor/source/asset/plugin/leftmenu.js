function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6471\" class=\"headerLeftMenuInActive\"><a id=\"aID6471\" href=\"#\" OnMouseOver=\"link('_dir','plugin0',this)\" class=\"leftMenuLinkHeadInActive\">plugin</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1062\" class=\"leftMenuInActive\"><a id=\"aID1062\" href=\"#\" OnMouseOver=\"link('_class','Plugin22463',this)\" class=\"leftMenuLinkInActive\">Plugin</a></div>\n");
document.write("<div id=\"divID1063\" class=\"leftMenuInActive\"><a id=\"aID1063\" href=\"#\" OnMouseOver=\"link('_class','PluginEditor22463',this)\" class=\"leftMenuLinkInActive\">PluginEditor</a></div>\n");
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
