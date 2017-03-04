function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6406\" class=\"headerLeftMenuInActive\"><a id=\"aID6406\" href=\"#\" OnMouseOver=\"link('_dir','component0',this)\" class=\"leftMenuLinkHeadInActive\">component</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID926\" class=\"leftMenuInActive\"><a id=\"aID926\" href=\"#\" OnMouseOver=\"link('_class','Component42087',this)\" class=\"leftMenuLinkInActive\">Component</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Macros</div>\n");
document.write("<div id=\"divID682\" class=\"leftMenuInActive\"><a id=\"aID682\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_Component2589292589',this)\" class=\"leftMenuLinkInActive\">COFFEE_Component</a></div>\n");
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
