function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6413\" class=\"headerLeftMenuInActive\"><a id=\"aID6413\" href=\"#\" OnMouseOver=\"link('_dir','control0',this)\" class=\"leftMenuLinkHeadInActive\">control</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID935\" class=\"leftMenuInActive\"><a id=\"aID935\" href=\"#\" OnMouseOver=\"link('_class','ApplicationControl3886',this)\" class=\"leftMenuLinkInActive\">ApplicationControl</a></div>\n");
document.write("<div id=\"divID936\" class=\"leftMenuInActive\"><a id=\"aID936\" href=\"#\" OnMouseOver=\"link('_class','ApplicationControlManager3886',this)\" class=\"leftMenuLinkInActive\">ApplicationControlManager</a></div>\n");
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
