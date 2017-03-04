function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6411\" class=\"headerLeftMenuInActive\"><a id=\"aID6411\" href=\"#\" OnMouseOver=\"link('_dir','application0',this)\" class=\"leftMenuLinkHeadInActive\">application</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6412\" class=\"leftMenuInActive\"><a id=\"aID6412\" href=\"#\" OnMouseOver=\"link('_dir','command/command0',this)\" class=\"leftMenuLinkInActive\">command</a></div>\n");
document.write("<div id=\"divID6413\" class=\"leftMenuInActive\"><a id=\"aID6413\" href=\"#\" OnMouseOver=\"link('_dir','control/control0',this)\" class=\"leftMenuLinkInActive\">control</a></div>\n");
document.write("<div id=\"divID6414\" class=\"leftMenuInActive\"><a id=\"aID6414\" href=\"#\" OnMouseOver=\"link('_dir','macros/macros0',this)\" class=\"leftMenuLinkInActive\">macros</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID933\" class=\"leftMenuInActive\"><a id=\"aID933\" href=\"#\" OnMouseOver=\"link('_class','Application3886',this)\" class=\"leftMenuLinkInActive\">Application</a></div>\n");
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
