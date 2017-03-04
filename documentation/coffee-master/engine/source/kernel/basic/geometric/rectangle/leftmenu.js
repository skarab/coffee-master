function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6278\" class=\"headerLeftMenuInActive\"><a id=\"aID6278\" href=\"#\" OnMouseOver=\"link('_dir','rectangle0',this)\" class=\"leftMenuLinkHeadInActive\">rectangle</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID738\" class=\"leftMenuInActive\"><a id=\"aID738\" href=\"#\" OnMouseOver=\"link('_class','Rectangle39014',this)\" class=\"leftMenuLinkInActive\">Rectangle</a></div>\n");
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
