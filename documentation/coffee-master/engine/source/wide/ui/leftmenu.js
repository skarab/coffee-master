function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6442\" class=\"headerLeftMenuInActive\"><a id=\"aID6442\" href=\"#\" OnMouseOver=\"link('_dir','ui0',this)\" class=\"leftMenuLinkHeadInActive\">ui</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6507\" class=\"leftMenuInActive\"><a id=\"aID6507\" href=\"#\" OnMouseOver=\"link('_dir','component/component0',this)\" class=\"leftMenuLinkInActive\">component</a></div>\n");
document.write("<div id=\"divID6432\" class=\"leftMenuInActive\"><a id=\"aID6432\" href=\"#\" OnMouseOver=\"link('_dir','macros/macros0',this)\" class=\"leftMenuLinkInActive\">macros</a></div>\n");
document.write("<div id=\"divID6438\" class=\"leftMenuInActive\"><a id=\"aID6438\" href=\"#\" OnMouseOver=\"link('_dir','property/property0',this)\" class=\"leftMenuLinkInActive\">property</a></div>\n");
document.write("<div id=\"divID6440\" class=\"leftMenuInActive\"><a id=\"aID6440\" href=\"#\" OnMouseOver=\"link('_dir','skin/skin0',this)\" class=\"leftMenuLinkInActive\">skin</a></div>\n");
document.write("<div id=\"divID6461\" class=\"leftMenuInActive\"><a id=\"aID6461\" href=\"#\" OnMouseOver=\"link('_dir','widget/widget0',this)\" class=\"leftMenuLinkInActive\">widget</a></div>\n");
document.write("<div id=\"divID6466\" class=\"leftMenuInActive\"><a id=\"aID6466\" href=\"#\" OnMouseOver=\"link('_dir','window/window0',this)\" class=\"leftMenuLinkInActive\">window</a></div>\n");
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
