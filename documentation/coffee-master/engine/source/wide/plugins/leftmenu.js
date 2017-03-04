function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6425\" class=\"headerLeftMenuInActive\"><a id=\"aID6425\" href=\"#\" OnMouseOver=\"link('_dir','plugins0',this)\" class=\"leftMenuLinkHeadInActive\">plugins</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6424\" class=\"leftMenuInActive\"><a id=\"aID6424\" href=\"#\" OnMouseOver=\"link('_dir','component/component0',this)\" class=\"leftMenuLinkInActive\">component</a></div>\n");
document.write("<div id=\"divID6511\" class=\"leftMenuInActive\"><a id=\"aID6511\" href=\"#\" OnMouseOver=\"link('_dir','macros/macros0',this)\" class=\"leftMenuLinkInActive\">macros</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID956\" class=\"leftMenuInActive\"><a id=\"aID956\" href=\"#\" OnMouseOver=\"link('_class','Library12811',this)\" class=\"leftMenuLinkInActive\">Library</a></div>\n");
document.write("<div id=\"divID957\" class=\"leftMenuInActive\"><a id=\"aID957\" href=\"#\" OnMouseOver=\"link('_class','Module12811',this)\" class=\"leftMenuLinkInActive\">Module</a></div>\n");
document.write("<div id=\"divID958\" class=\"leftMenuInActive\"><a id=\"aID958\" href=\"#\" OnMouseOver=\"link('_class','Object12811',this)\" class=\"leftMenuLinkInActive\">Object</a></div>\n");
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
