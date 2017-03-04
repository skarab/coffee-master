function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6356\" class=\"headerLeftMenuInActive\"><a id=\"aID6356\" href=\"#\" OnMouseOver=\"link('_dir','font0',this)\" class=\"leftMenuLinkHeadInActive\">font</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID858\" class=\"leftMenuInActive\"><a id=\"aID858\" href=\"#\" OnMouseOver=\"link('_class','Font54809',this)\" class=\"leftMenuLinkInActive\">Font</a></div>\n");
document.write("<div id=\"divID859\" class=\"leftMenuInActive\"><a id=\"aID859\" href=\"#\" OnMouseOver=\"link('_class','FontGlyph54809',this)\" class=\"leftMenuLinkInActive\">FontGlyph</a></div>\n");
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
