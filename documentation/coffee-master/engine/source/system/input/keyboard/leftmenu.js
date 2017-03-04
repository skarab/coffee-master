function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6391\" class=\"headerLeftMenuInActive\"><a id=\"aID6391\" href=\"#\" OnMouseOver=\"link('_dir','keyboard0',this)\" class=\"leftMenuLinkHeadInActive\">keyboard</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID906\" class=\"leftMenuInActive\"><a id=\"aID906\" href=\"#\" OnMouseOver=\"link('_class','Key26233',this)\" class=\"leftMenuLinkInActive\">Key</a></div>\n");
document.write("<div id=\"divID907\" class=\"leftMenuInActive\"><a id=\"aID907\" href=\"#\" OnMouseOver=\"link('_class','Keyboard26233',this)\" class=\"leftMenuLinkInActive\">Keyboard</a></div>\n");
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
