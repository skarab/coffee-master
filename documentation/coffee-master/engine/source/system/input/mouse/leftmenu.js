function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6392\" class=\"headerLeftMenuInActive\"><a id=\"aID6392\" href=\"#\" OnMouseOver=\"link('_dir','mouse0',this)\" class=\"leftMenuLinkHeadInActive\">mouse</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID908\" class=\"leftMenuInActive\"><a id=\"aID908\" href=\"#\" OnMouseOver=\"link('_class','Mouse26233',this)\" class=\"leftMenuLinkInActive\">Mouse</a></div>\n");
document.write("<div id=\"divID909\" class=\"leftMenuInActive\"><a id=\"aID909\" href=\"#\" OnMouseOver=\"link('_class','MouseButton26233',this)\" class=\"leftMenuLinkInActive\">MouseButton</a></div>\n");
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
